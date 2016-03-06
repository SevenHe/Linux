from django.http import HttpResponse, HttpResponseRedirect
from django.template import RequestContext
from django.shortcuts import render, render_to_response
from django.contrib.auth.decorators import login_required  
from Profile.models import UserProfile
from Profile.forms import AvatarUploadForm
from TicketManagementSystem.settings import MEDIA_ROOT

import Image
import cStringIO
# custom views!
@login_required(login_url='/account/turn_to_sign_in/')
def user_avatar(request):
    # for security, get the path, and return a img!
    user_id = request.user.id;
    try:
        user_profile = UserProfile.objects.get(user_id=user_id)
    except:
        return HttpResponse('Unknown error!')
    else:
        img = Image.open(user_profile.avatar)
        buf = cStringIO.StringIO()
        img.save(buf, 'png')
        return HttpResponse(buf.getvalue(), 'image/png')

@login_required(login_url='/account/turn_to_sign_in/')
def require_avatar(request):
    if request.GET['rsui']:
        user_id = request.GET['rsui'][2:-2]
    else:
        return HttpResponse("Illegal access!")
    try:
        user_profile = UserProfile.objects.get(user_id=user_id)
    except:
        return HttpResponse('Unknown error!')
    else:
        img = Image.open(user_profile.avatar)
        buf = cStringIO.StringIO()
        img.save(buf, 'png')
        return HttpResponse(buf.getvalue(), 'image/png')

@login_required(login_url='/account/turn_to_sign_in/')
def upload_avatar(request):
    if request.method == 'POST':
        # if post, this is a good way!
        upload_form = AvatarUploadForm(request.POST, request.FILES)
        if upload_form.is_valid():    
            try:
                user_profile = UserProfile.objects.get(user_id=request.user.id)
            except:
                return HttpResponse("Illegal access!")
            else:
                if upload_form.cleaned_data['avatar'].size > 1000000:
                    return HttpResponse("1M")
                user_profile.avatar = upload_form.cleaned_data['avatar']
                # I doubt if i should do this in server script
                # I think do this use a script manually is more security
                # This is the worst choice!!
                #import os
                #if os.listdir(MEDIA_ROOT+'user_'+request.user.id):
                #    pass
                user_profile.save()
                return HttpResponse("success")
        else:
            return HttpResponse("invalid"+request.FILES)
    else:
        return HttpResponse("UPLOAD UNKNOWN ERROR!!!"+request.method+request.FILES)
