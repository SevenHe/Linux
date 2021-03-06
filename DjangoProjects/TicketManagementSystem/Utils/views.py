# -*- encoding: utf-8 -*-
from django.shortcuts import render, render_to_response 
from django.contrib.auth.models import User
from django.contrib.auth.decorators import login_required  
from django.template import RequestContext
from django.http import HttpResponse, Http404
# Create your views here.
import random
from smtplib import SMTP_SSL
from email.mime.text import MIMEText
from TicketManagementSystem.settings import EMAIL_HOST_PASSWORD
from Utils.models import EmailCaptcha, UserComment
import Image, ImageDraw, ImageFont, ImageFilter

_letter_cases = "abcdefghjkmnpqrstuvwxy" # 小写字母，去除可能干扰的i，l，o，z
_upper_cases = _letter_cases.upper() # 大写字母
_numbers = ''.join(map(str, range(3, 10))) # 数字
init_chars = ''.join((_letter_cases, _upper_cases, _numbers))
fontType="/usr/share/fonts/truetype/freefont/FreeSans.ttf"

def create_diag_code(
        size=(120, 30),
        chars=init_chars,
        img_type="GIF",
        mode="RGB",
        bg_color=(255, 255, 255),
        fg_color=(0, 0, 255),
        font_size=18,
        font_type=fontType,
        length=4,
        draw_lines=True,
        n_line=(1, 2),
        draw_points=True,
        point_chance = 2):
    '''
        @todo: 生成验证码图片
        @param size: 图片的大小，格式（宽，高），默认为(120, 30)
        @param chars: 允许的字符集合，格式字符串
        @param img_type: 图片保存的格式，默认为GIF，可选的为GIF，JPEG，TIFF，PNG
        @param mode: 图片模式，默认为RGB
        @param bg_color: 背景颜色，默认为白色
        @param fg_color: 前景色，验证码字符颜色，默认为蓝色#0000FF
        @param font_size: 验证码字体大小
        @param font_type: 验证码字体，默认为 ae_AlArabiya.ttf
        @param length: 验证码字符个数
        @param draw_lines: 是否划干扰线
        @param n_lines: 干扰线的条数范围，格式元组，默认为(1, 2)，只有draw_lines为True时有效
        @param draw_points: 是否画干扰点
        @param point_chance: 干扰点出现的概率，大小范围[0, 100]
        @return: [0]: PIL Image实例
        @return: [1]: 验证码图片中的字符串
    '''
    width, height = size # 宽， 高
    img = Image.new(mode, size, bg_color) # 创建图形
    draw = ImageDraw.Draw(img) # 创建画笔
    if draw_lines:
        create_lines(draw,n_line,width,height)
    if draw_points:
        create_points(draw,point_chance,width,height)
    strs = create_strs(draw,chars,length,font_type, font_size,width,height,fg_color)
    # 图形扭曲参数
    params = [1 - float(random.randint(1, 2)) / 100, 0, 0, 0,
            1 - float(random.randint(1, 10)) / 100,                                                     
            float(random.randint(1, 2)) / 500,
            0.001,
            float(random.randint(1, 2)) / 500]

    img = img.transform(size, Image.PERSPECTIVE, params) # 创建扭曲

    img = img.filter(ImageFilter.EDGE_ENHANCE_MORE) # 滤镜，边界加强（阈值更大）
    
    return img, strs


def create_lines(draw,n_line,width,height):
    '''绘制干扰线'''
    line_num = random.randint(n_line[0],n_line[1]) # 干扰线条数

    for i in range(line_num):
        # 起始点
        begin = (random.randint(0, width), random.randint(0, height))
        #结束点
        end = (random.randint(0, width), random.randint(0, height))
        draw.line([begin, end], fill=(0, 0, 0))

def create_points(draw,point_chance,width,height):
    '''绘制干扰点'''
    chance = min(100, max(0, int(point_chance))) # 大小限制在[0, 100]
    for w in xrange(width):
        for h in xrange(height):
            tmp = random.randint(0, 100)
            if tmp > 100 - chance:
                draw.point((w, h), fill=(0, 0, 0))


def create_strs(draw,chars,length,font_type, font_size,width,height,fg_color):
    '''绘制验证码字符'''
    '''生成给定长度的字符串，返回列表格式'''
    c_chars = random.sample(chars, length)
    strs = ' %s ' % ' '.join(c_chars) # 每个字符前后以空格隔开
    font = ImageFont.truetype(font_type, font_size)
    font_width, font_height = font.getsize(strs)                                                    
    draw.text(((width - font_width) / 3, (height - font_height) / 3),strs, font=font, fill=fg_color)
    
    return ''.join(c_chars)

# own async SSL email sender!
def async_sender(rcp, html_content):
    import threading
    t = threading.Thread(target=send_email, args=[rcp, html_content])
    t.start()


def send_email(rcp, html_content):
    msg = MIMEText(html_content, 'html', 'utf-8')
    msg['Subject'] = '用户激活'
    msg['From'] = '5036 购物中心'
    conn = SMTP_SSL('smtp.qq.com', port=465)
    conn.login("961950442@qq.com", EMAIL_HOST_PASSWORD)
    tolist = [rcp]
    try:
        conn.sendmail('961950442@qq.com', tolist, msg.as_string())
    finally:
        conn.quit()

def activate(request):
    if ('username'.encode('hex') and 'captcha'.encode('hex')) in request.GET:
        username = request.GET['username'.encode('hex')].decode('hex')[0:-4]
        captcha = request.GET['captcha'.encode('hex')]
        delete = True
        try: 
            user = User.objects.get(username=username)
            ec = EmailCaptcha.objects.get(user_id=user.id)
        except:
            delete = False
        if captcha == ec.captcha:
            post_date = ec.post_date
            from datetime import datetime
            now = datetime.now()
            if now.year == post_date.year and now.month == post_date.month and now.day == post_date.day:
                if (now.hour == post_date.hour and now.minute - post_date.minute <= 10) or (now.hour > post_date.hour and now.minute - post_date.minute < 0 and (now.minute - post_date.minute) % 60 <= 10):
                    user.is_active = True
                    user.save()
                    result = '用户激活成功！'
                    resend = False
                else:
                    result = '验证码已失效！'
                    resend = True
            else:
                result = '验证码已不翼而飞...'
                resend = True
        else:
            result = '验证码不匹配，可能是由网络不畅等原因引起！'
            resend = True

        if delete:
            ec.delete()
    else:
        resutl = '链接不合法!'
        resend = True
                    
    return render_to_response('activation.html', {'result': result, 'resend': resend}, context_instance=RequestContext(request))

# need to do some db queries!
def resend(request):
    pass

@login_required(login_url='/account/turn_to_sign_in/')
def feedback(request):
    try:
        comments = UserComment.objects.all()
    except:
        return HttpResponse(status=500)
    else:
        return render_to_response('feedback.html', {'comments': comments}, context_instance=RequestContext(request))

def submit_comment(request):
    if not request.is_ajax():
        raise Http404
    comment = request.POST['comment']
    user_id = request.POST['user']
    try:
        user_comment = UserComment(user_id=user_id, comment=comment)
        user_comment.save()
    except:
        return HttpResponse("error")
    else:
        return HttpResponse("ok")

def aboutus(request):
    return render_to_response('aboutus.html', context_instance=RequestContext(request))

def contact(request):
    return render_to_response('connection.html', context_instance=RequestContext(request))

