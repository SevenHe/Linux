# -*- encoding: utf-8 -*-
"""
Django settings for TicketManagementSystem project.

Generated by 'django-admin startproject' using Django 1.8.4.

For more information on this file, see
https://docs.djangoproject.com/en/1.8/topics/settings/

For the full list of settings and their values, see
https://docs.djangoproject.com/en/1.8/ref/settings/
"""

# Build paths inside the project like this: os.path.join(BASE_DIR, ...)
import os

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


# Quick-start development settings - unsuitable for production
# See https://docs.djangoproject.com/en/1.8/howto/deployment/checklist/

# SECURITY WARNING: keep the secret key used in production secret!
SECRET_KEY = 'd#084qvfc)*_w^%#-^g511ry$62gt0shyjlol7r*k2%2wald(2'

# SECURITY WARNING: don't run with debug turned on in production!
DEBUG = True 

ALLOWED_HOSTS = ['127.0.0.1', '49.140.62.120']


# Application definition

INSTALLED_APPS = (
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'Utils',
    'tickets',
    'Profile',
)

MIDDLEWARE_CLASSES = (
    'django.middleware.security.SecurityMiddleware',
    'django.middleware.cache.UpdateCacheMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.auth.middleware.SessionAuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
    'django.middleware.cache.FetchFromCacheMiddleware',
)

ROOT_URLCONF = 'TicketManagementSystem.urls'

TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [BASE_DIR + '/Templates'],
        'APP_DIRS': True,
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.core.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
            ],
        },
    },
]

WSGI_APPLICATION = 'TicketManagementSystem.wsgi.application'


# Database
# https://docs.djangoproject.com/en/1.8/ref/settings/#databases

DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.oracle',
        'NAME': 'XE',
        'USER': 'SEVEN',
        'PASSWORD': 'Seven1001',
        'HOST':'127.0.0.1',
        'PORT':'1521',
    }
}


# Internationalization
# https://docs.djangoproject.com/en/1.8/topics/i18n/

LANGUAGE_CODE = 'en-us'

LANGUAGES = (
    ('en', u"English"),
    ('zh-cn', u"简体中文"),
    )

# TIME_ZONE = 'UTC'             # not for USA!

# To use 'django.utils.translation' for I18N, and 
# You must take tokens to indicate which strings should be translated, and
# use alias to take into more effects.
USE_I18N = True

USE_L10N = True

#USE_TZ = True

#SEND_BROKEN_LINK_EMAILS = True

# Static files (CSS, JavaScript, Images)
# https://docs.djangoproject.com/en/1.8/howto/static-files/
STATIC_ROOT = os.path.join(BASE_DIR, "static/")
STATIC_URL = '/static/'

# Media files (multi-media files...)
MEDIA_ROOT = os.path.join(BASE_DIR, "media/")
MEDIA_URL = '/media/'

ADMINS = (
    ('Seven', 'sevenhe2015@gmail.com'),
    )
MANAGERS = (
    ('Seven', 'sevenhe2015@gmail.com'),
    )

# memcache 
CACHE_BACKEND = 'file:///var/tmp/django_cache'

# This can be improved by SSL, this is so tough, do my send program!
EMAIL_HOST_PASSWORD = 'Seven1001'
EMAIL_HOST = 'smtp.gmail.com'
EMAIL_PORT = 465
EMAIL_HOST_USER = 'sevenhe2015@gmail.com'
EMAIL_SUBJECT_PREFIX = u'[5036 购票中心]'           #为邮件Subject-line前缀,默认是'[django]
EMAIL_USE_TLS = True                                #与SMTP服务器通信时，是否启动TLS链接(安全链接)。默认是false
#管理员站点
EMAIL_BACKEND = 'django.core.mail.backends.smtp.EmailBackend'

#APPEND_SLASH = False
#SERVER_EMAIL = 'xinxinyu2011@163.com'              #The email address that error messages come from, such as those sent to ADMINS and MANAGERS.

# Custom settings
CUSTOM_SETTINGS = {}
CUSTOM_SETTINGS['ACTIVATION_URL'] = '49.140.62.120/account/activation'
CUSTOM_SETTINGS['ACTIVATION_HTML_CONTENT'] = "<p>感谢您对<strong>5036 购票中心</strong>的支持，请点击此链接激活您的账号：<a href='%s'>%s</a> （10分钟内有效）</p><br/><p>（若链接无法点击，请完整复制到浏览器中进行激活）</p>"
CUSTOM_SETTINGS['SALT'] = '5036TS'
