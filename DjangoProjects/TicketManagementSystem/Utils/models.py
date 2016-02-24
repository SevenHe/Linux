# -*- encoding: utf-8 -*-
from django.db import models
from django.contrib.auth.models import User

# ForeignKey, is related to the PrimaryKey, and the model, 
# the most important thing is that it saves the foreign model as a name_id key, do not be absorbed by it literal look.
# you need to use the xx_set.filter/get and other methods to operate them, and specify the keyword to create!
# and when you create an object, you need to specify the id, it means: .objects.create(user_id=?)
class EmailCaptcha(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    captcha = models.CharField(max_length=32)
    post_date = models.DateTimeField()


