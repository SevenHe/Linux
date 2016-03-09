"""TicketManagementSystem URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.8/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home') !!
Class-based views     ------app is not site.
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Add an import:  from blog import urls as blog_urls
    2. Add a URL to urlpatterns:  url(r'^blog/', include(blog_urls))
"""
from django.conf.urls import include, url
from django.contrib import admin
from TicketManagementSystem.views import *
from Utils.views import *
from tickets.views import *
from Profile.views import *

# this can be divided into different apps' urls.py, but i just use this to see clearly!
urlpatterns = [
    url(r'^admin/', include(admin.site.urls)),
    url(r'^$', preview),
    url(r'^index$', index, name='index'),
    url(r'^account/sign_up$', sign_up, name='sign_up'),
    url(r'^account/sign_in/$', sign_in, name='sign_in'),
    url(r'^account/sign_out/$', sign_out, name='sign_out'),
    url(r'^account/turn_to_sign_in/$', turn_to_sign_in, name='turn_to_sign_in'),
    url(r'^account/personal/$', personalize, name='personalize'),
    url(r'^account/diag_code$', diag_code),
    url(r'^account/avatar/$', user_avatar, name='user_avatar'),
    url(r'^account/require_avatar/$', require_avatar, name='require_avatar'),
    url(r'^account/upload_avatar/$', upload_avatar, name='upload_avatar'),
    url(r'^account/sign_up/success$', sign_up_success, name='log_success'),
    url(r'^account/activation$', activate, name='activation'),
    url(r'^account/resend/$', resend, name='resend'),
    url(r'^account/feedback/$', feedback, name='feedback'),
    url(r'^account/feedback/submit/$', submit_comment, name='submit_comment'),
    url(r'^account/aboutus/$', aboutus, name='aboutus'),
    url(r'^account/contact/$', contact, name='contact'),
    url(r'^ticket/train/query/$', train_business, name='train_business'),
    url(r'^ticket/train/ajax_get/$', ajax_get_train, name='ajax_get_train'),
    url(r'^ticket/bus/query/$', bus_business, name='bus_business'),
    url(r'^ticket/bus/ajax_get/$', ajax_get_bus, name='ajax_get_bus'),
    url(r'^ticket/fly/query/$', fly_business, name='fly_business'),
    url(r'^ticket/fly/ajax_get/$', ajax_get_fly, name='ajax_get_fly'),
    url(r'^ticket/reserve/$', reservation, name='reservation'),
    url(r'ticket/trade/(?P<t_type>[a-zA-Z]{0,6})/$', trade, name='trade'),
    url(r'ticket/pay/$', payment, name='payment'),
    url(r'ticket/cancel/$', cancel, name='cancel'),
    #url(r'^account/test$', sign_up),
]
