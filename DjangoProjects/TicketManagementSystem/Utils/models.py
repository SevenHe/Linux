# -*- encoding: utf-8 -*-
from django.db import models
from django.contrib.auth.models import User

class EmailCaptcha(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    captcha = models.CharField(max_length=32)
    post_date = models.DateTimeField()


