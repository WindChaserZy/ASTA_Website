# Generated by Django 3.1.4 on 2021-01-02 18:02

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0036_auto_20210102_1755'),
    ]

    operations = [
        migrations.AddField(
            model_name='contest',
            name='timeUp',
            field=models.DateTimeField(default=django.utils.timezone.now),
            preserve_default=False,
        ),
    ]
