# Generated by Django 3.1.4 on 2021-02-03 22:49

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0045_game_gameai_gamebot_gamebotplay_gamebotscore_gamerecord'),
    ]

    operations = [
        migrations.AddField(
            model_name='game',
            name='timestamp',
            field=models.DateTimeField(auto_now_add=True, default=django.utils.timezone.now),
            preserve_default=False,
        ),
    ]
