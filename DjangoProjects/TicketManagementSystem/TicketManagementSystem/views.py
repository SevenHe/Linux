# -*- encoding: utf-8 -*-
"""
must pay attention to the syntax issues.
"""
from django.http import HttpResponse
from django.shortcuts import render, render_to_response
from django.core.context_processors import csrf
# from TestModule.models import Test
# from HelloWorld.forms import ContactForm
# from datetime import *

def index(request):
	return render_to_response('index.html')


def hello(request):
    context = {}
    context['hello'] = 'Hello World!'
    return render(request, 'hello.html', context)
  
    
def testdb_insert(request):
	test1 = Test(name='w3cschool.cc')
	test1.save()
	return HttpResponse("<p>数据添加成功！</p>")
	
	
def testdb_get(request):
	# 初始化
	response = ""
	response1 = ""
	
	
	# 通过objects这个模型管理器的all()获得所有数据行，相当于SQL中的SELECT * FROM
	list = Test.objects.all()
		
	# the database will add a primary key for the data, but the id will not be return to 1 after deletion
	# filter相当于SQL中的WHERE，可设置条件过滤结果
	#response2 = Test.objects.filter(id=1) 
	
	# 获取单个对象
	#response3 = Test.objects.get(id=1) 
	
	# 限制返回的数据 相当于 SQL 中的 OFFSET 0 LIMIT 2;
	#Test.objects.order_by('name')[0:2]
	
	#数据排序
	#Test.objects.order_by("id")
	
	# 上面的方法可以连锁使用
	#Test.objects.filter(name="w3cschool.cc").order_by("id")
	
	# 输出所有数据
	for var in list:
		response1 += var.name + " "
	response = response1
	return HttpResponse("<p>" + response + "</p>")
	

def testdb_update(request):
	# 修改其中一个id的name字段，再save，相当于SQL中的UPDATE
	# use the update method to avoid updating the all data fiels by using save().
	tid = 1
	get = 0
	while get == 0:
		try:
			Test.objects.get(id=tid)
		except Test.DoesNotExist:
			tid += 1
		else:	
			get = 1
			Test.objects.filter(id=tid).update(name='w3cschool菜鸟教程')
	
	# 另外一种方式
	#Test.objects.filter(id=1).update(name='w3cschool菜鸟教程')
	
	# 修改所有的列
	# Test.objects.all().update(name='w3cschool菜鸟教程')
	
	return HttpResponse("<p>修改成功</p>")
	
	
def testdb_delete(request):
	# 删除id=1的数据
	#test1 = Test.objects.get(id=1)
	#test1.delete()
	
	# 另外一种方式
	# Test.objects.filter(id=1).delete()
	
	# 删除所有数据
	# Test.objects.all().delete()
	tid = 1
	get = 0
	while get == 0:
		try:
			test1 = Test.objects.get(id=tid)
		except Test.DoesNotExist:
			tid += 1
		else:	
			get = 1
			test1.delete()
	
	return HttpResponse("<p>删除成功</p>")
	

# 表单
def search_form(request):
	return render_to_response('search_form.html')


# 接收请求数据
def search(request):  
	request.encoding='utf-8'
	if 'q' in request.GET:
		message = '你搜索的内容为: ' + request.GET['q'].encode('utf-8')
	else:
		message = '你提交了空表单'
	return HttpResponse(message)


""" a better way to search in reality.
def search(request):
    if 'q' in request.GET and request.GET['q']:
	            q = request.GET['q']
	            books = Book.objects.filter(title__icontains=q)
	            return render_to_response('search_results.html',
			                {'books': books, 'query': q})
    else:
		    return render_to_response('search_form.html', {'error': True})
"""


def search_post(request):
	# ctx--context
	ctx ={}
	# get default data 
	ctx.update(csrf(request))
	if request.POST:
		ctx['rlt'] = request.POST['q']
	return render(request, "post.html", ctx)


# Or use a try/except.
def ua_display_good(request):
    ua = request.META.get('HTTP_USER_AGENT', 'unknown')
    return HttpResponse("Your browser is %s" % ua)

"""
should change the following code to use a render method to get in a html.
def display_meta(request):
    values = request.META.items()
        values.sort()
	    html = []
	        for k, v in values:
			        html.append('<tr><td>%s</td><td>%s</td></tr>' % (k, v))
				    return HttpResponse('<table>%s</table>' % '\n'.join(html))
"""


# more capable way is to use django.forms, and add forms into forms.py
# rewrite it!
def contact(request):
    if request.method == 'POST':
        form = ContactForm(request.POST)
        if form.is_valid():
            cd = form.cleaned_data
            send_mail(
	                cd['subject'],
	                cd['message'],
	                cd.get('email', 'noreply@example.com'),
	                ['siteowner@example.com'],
	            )
        return HttpResponseRedirect('/contact/thanks/')
    else:
        form = ContactForm()
	return render_to_response('contact_form.html', {'form': form})
"""
def original_contact(request):
   	errors = []
	if request.method == 'POST':
        if not request.POST.get('subject', ''):
            errors.append('Enter a subject.')
        if not request.POST.get('message', ''):
            errors.append('Enter a message.')
        if request.POST.get('email') and '@' not in request.POST['email']:
            errors.append('Enter a valid e-mail address.')
        if not errors:
            send_mail(
		  request.POST['subject'],
		  request.POST['message'],
		  request.POST.get('email', 'noreply@example.com'),
		  ['siteowner@example.com'],
	    )
		# avoid sending two emails due to the successful request
		# so need to do redirection!
	    return HttpResponseRedirect('/contact/thanks/')
	return render_to_response('contact_form.html', {'errors': errors})
"""

# search for open code way in searching in a whole database on the Internet, to get the best way to search in a database, rather than 'icontains' way!
