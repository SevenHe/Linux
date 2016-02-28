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
    genre = models.CharField(max_length=1)
    price = models.DecimalField(max_digits=5, decimal_places=1)
    quantity = models.IntegerField()


class Trade(models.Model):
    STATUS_CHOICES = (
            (1, 'BOOKED'),
            (2, 'BOUGHT'),
            (3, 'DISABLED'),
            )
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    serial = models.ForeignKey(TrainTicket)
    book_date = models.DateTimeField()
    number = models.IntegerField(default=1)
    status = models.IntegerField(default=1, choices=STATUS_CHOICES)

