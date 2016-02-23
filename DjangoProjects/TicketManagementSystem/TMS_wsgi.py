#!/usr/bin/env python
# coding:utf-8

import os
import sys

reload(sys)
sys.setdefaultencoding("utf8")

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "TicketManagementSystem.settings")

from django.core.wsgi import get_wsgi_application  

application = get_wsgi_application()

import uwsgi  
from uwsgidecorators import timer  
from django.utils import autoreload  
 
@timer(3)  
def change_code_gracefull_reload(sig):  
    if autoreload.code_changed():  
        uwsgi.reload()
