# Generated by Django 3.1.4 on 2020-12-16 23:18

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0031_auto_20201216_2317'),
    ]

    operations = [
        migrations.AlterField(
            model_name='contest',
            name='registerTimeUp',
            field=models.DateTimeField(),
        ),
        migrations.AlterField(
            model_name='contest',
            name='timeUp',
            field=models.DateTimeField(),
        ),
    ]