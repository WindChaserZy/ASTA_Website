# Generated by Django 3.0.2 on 2020-08-12 09:02

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0005_token'),
    ]

    operations = [
        migrations.AlterField(
            model_name='token',
            name='email',
            field=models.CharField(default='', max_length=60, primary_key=True, serialize=False),
        ),
        migrations.AlterField(
            model_name='user',
            name='email',
            field=models.CharField(default='', max_length=60),
        ),
    ]
