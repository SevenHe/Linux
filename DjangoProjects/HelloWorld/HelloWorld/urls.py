"""HelloWorld URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.8/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Add an import:  from blog import urls as blog_urls
    2. Add a URL to urlpatterns:  url(r'^blog/', include(blog_urls))
"""
from django.conf.urls import include, url
from django.contrib import admin
from HelloWorld.views import *
from TestModule.models import *

# once the module is changed, the * could be not useful. 

urlpatterns = [
    url(r'^admin/', include(admin.site.urls)),
    url(r'^$', index),
    url(r'^hello/$', hello),
    url(r'^testdb_insert/$', testdb_insert),
    url(r'^testdb_get/$', testdb_get),
    url(r'^testdb_update/$', testdb_update),
    url(r'^testdb_delete/$', testdb_delete),
    url(r'^search-form/$', search_form),
	url(r'^search/$', search),
	url(r'^search-post/$', search_post),
]
