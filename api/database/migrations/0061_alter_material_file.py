# Generated by Django 3.2.15 on 2022-10-27 17:08

import database.models
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0060_material_file'),
    ]

    operations = [
        migrations.AlterField(
            model_name='material',
            name='file',
            field=models.FileField(blank=True, null=True, upload_to=database.models.Mt_dirpath),
        ),
    ]
