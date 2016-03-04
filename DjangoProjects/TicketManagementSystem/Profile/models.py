# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models
from django.contrib.auth.models import User
# Create your models here.

def user_avatar_path(instance, filename):
    # image will be save at MEDIA_ROOT/user_id/filename
    return 'user_{0}/{1}'.format(instance.user.id, filename)

class UserProfile(models.Model):
    # This place can be replaced by os.path.join(settings.BASE_DIR, ... ...)
    # Now, for the test site, i use this and i don't know if it would cause security issues!
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    avatar = models.ImageField(upload_to=user_avatar_path, 
                            default='/home/seven/Code/DjangoProjects/TicketManagementSystem/static/images/1.jpg',
                            height_field='avatar_height',
                            width_field='avatar_width')
    avatar_height = models.PositiveIntegerField(blank=True, default=0)
    avatar_width = models.PositiveIntegerField(blank=True, default=0)
    phone_number = models.CharField(max_length=11, null=True)

