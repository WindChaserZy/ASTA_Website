# Generated by Django 3.2.5 on 2021-10-10 15:11

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0054_auto_20210207_1603'),
    ]

    operations = [
        migrations.AddField(
            model_name='user',
            name='wechatId',
            field=models.CharField(blank=True, default='', max_length=60),
        ),
        migrations.AlterField(
            model_name='gamebot',
            name='addition',
            field=models.CharField(blank=True, default='', max_length=128),
        ),
    ]
