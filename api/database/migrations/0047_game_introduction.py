# Generated by Django 3.1.4 on 2021-02-04 11:41

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0046_game_timestamp'),
    ]

    operations = [
        migrations.AddField(
            model_name='game',
            name='introduction',
            field=models.CharField(default='', max_length=1024),
        ),
    ]
