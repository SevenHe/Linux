# -*- coding: utf-8 -*-
# Generated by Django 1.9 on 2016-03-03 12:16
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('tickets', '0003_auto_20160303_0539'),
    ]

    operations = [
        migrations.AlterField(
            model_name='flytrade',
            name='genre',
            field=models.CharField(choices=[('f', '\u5934\u7b49\u8231'), ('e', '\u7ecf\u6d4e\u8231')], default='e', max_length=1),
        ),
    ]
