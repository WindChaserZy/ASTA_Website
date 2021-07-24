# Generated by Django 3.1.6 on 2021-02-07 16:03

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0053_auto_20210207_1317'),
    ]

    operations = [
        migrations.AddField(
            model_name='gamerecord',
            name='bot',
            field=models.ManyToManyField(related_name='record', through='database.GameBotPlay', to='database.GameBot'),
        ),
        migrations.AlterField(
            model_name='game',
            name='introduction',
            field=models.CharField(blank=True, default='', max_length=1024),
        ),
    ]