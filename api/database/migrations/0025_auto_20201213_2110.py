# Generated by Django 3.1.2 on 2020-12-13 21:10

import database.models
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0024_auto_20201213_0226'),
    ]

    operations = [
        migrations.AlterField(
            model_name='problemsubmission',
            name='code',
            field=models.FileField(null=True, upload_to=database.models.PS_dirpath),
        ),
    ]
