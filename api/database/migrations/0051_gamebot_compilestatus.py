# Generated by Django 3.1.4 on 2021-02-06 19:38

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0050_auto_20210205_1546'),
    ]

    operations = [
        migrations.AddField(
            model_name='gamebot',
            name='compileStatus',
            field=models.IntegerField(default=0),
        ),
    ]
