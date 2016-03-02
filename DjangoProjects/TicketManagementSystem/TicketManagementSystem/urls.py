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

urlpatterns = [
    url(r'^admin/', include(admin.site.urls)),
    url(r'^$', preview),
    url(r'^index$', index, name='index'),
    url(r'^account/sign_up$', sign_up, name='sign_up'),
    url(r'^account/sign_in/$', sign_in, name='sign_in'),
    url(r'^account/sign_out/$', sign_out, name='sign_out'),
    url(r'^account/(?P<username>[0-9a-zA-z]{6, 16})/$', personalize, name='personalize'),
    url(r'^account/diag_code$', diag_code),
    url(r'^account/sign_up/success$', sign_up_success, name='log_success'),
    url(r'^account/activation$', activate, name='activation'),
    url(r'^account/resend/$', resend, name='resend'),
    url(r'^ticket/train/query/$', train_business, name='train_business'),
    url(r'^ticket/train/ajax_get/$', ajax_get_train, name='ajax_get_train'),
    #url(r'^account/test$', sign_up),
]
