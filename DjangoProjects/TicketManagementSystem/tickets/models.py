# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models
from django.contrib.auth.models import User

# Create your models here.
class TrainTicket(models.Model):
    serial = models.CharField(max_length=4)
    start = models.CharField(max_length=10)
    terminus = models.CharField(max_length=10)
    departure = models.DateTimeField()
    last = models.IntegerField()
    price = models.DecimalField(max_digits=5, decimal_places=1)
    quantity = models.IntegerField()

class FlyTicket(models.Model):
    serial = models.CharField(max_length=6)
    start = models.CharField(max_length=10)
    terminus = models.CharField(max_length=10)
    departure = models.DateTimeField()
    last = models.IntegerField()
    price = models.DecimalField(max_digits=6, decimal_places=1)
    quantity = models.IntegerField()

class BusTicket(models.Model):
    serial = models.CharField(max_length=4)
    start = models.CharField(max_length=10)
    terminus = models.CharField(max_length=10)
    departure = models.DateTimeField()
    last = models.IntegerField()
    price = models.DecimalField(max_digits=5, decimal_places=1)
    quantity = models.IntegerField()

class TrainTrade(models.Model):
    STATUS_CHOICES = ( 
            (1, 'BOOKED'),
            (2, 'BOUGHT'),
            (3, 'DISABLED'),
            ) 
    GENRE_CHOICES = (
            ('h', '硬座'),
            ('s', '卧铺'),
            )
    TYPE_CHOICES = (
            ('a', '成人票'),
            ('c', '儿童票'),
            )
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    serial = models.ForeignKey(TrainTicket)
    book_date = models.DateTimeField()
    genre = models.CharField(default='h', max_length=1, choices=GENRE_CHOICES)      # for adult, child, hard seat, sleeper
    t_type = models.CharField(default='a', max_length=1, choices=TYPE_CHOICES) 
    number = models.IntegerField(default=1)
    status = models.IntegerField(default=1, choices=STATUS_CHOICES)

class BusTrade(models.Model):
    STATUS_CHOICES = ( 
            (1, 'BOOKED'),
            (2, 'BOUGHT'),
            (3, 'DISABLED'),
            ) 
    GENRE_CHOICES = (
            ('h', '硬座'),
            ('u', '软座'),
            )
    TYPE_CHOICES = (
            ('a', '成人票'),
            ('s', '特殊票'),
            )
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    serial = models.ForeignKey(BusTicket)
    book_date = models.DateTimeField()
    genre = models.CharField(default='h', max_length=1, choices=GENRE_CHOICES)
    t_type = models.CharField(default='a', max_length=1, choices=TYPE_CHOICES)
    number = models.IntegerField(default=1)
    status = models.IntegerField(default=1, choices=STATUS_CHOICES)

class FlyTrade(models.Model):
    STATUS_CHOICES = ( 
            (1, 'BOOKED'),
            (2, 'BOUGHT'),
            (3, 'DISABLED'),
            ) 
    GENRE_CHOICES = (
            ('f', '头等舱'),
            ('e', '经济舱'),
            )
    TYPE_CHOICES = (
            ('w', '全价票'),
            ('p', '特价票'),
            )
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    serial = models.ForeignKey(FlyTicket)
    book_date = models.DateTimeField()
    genre = models.CharField(default='e', max_length=1, choices=GENRE_CHOICES)
    t_type = models.CharField(default='w', max_length=1, choices=TYPE_CHOICES)
    number = models.IntegerField(default=1)
    status = models.IntegerField(default=1, choices=STATUS_CHOICES)

