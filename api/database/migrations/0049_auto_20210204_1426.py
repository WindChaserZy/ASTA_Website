# Generated by Django 3.1.4 on 2021-02-04 14:26

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0048_auto_20210204_1424'),
    ]

    operations = [
        migrations.RenameField(
            model_name='gameai',
            old_name='title',
            new_name='name',
        ),
        migrations.AddField(
            model_name='gameai',
            name='introduction',
            field=models.CharField(default='', max_length=1024),
        ),
        migrations.AlterField(
            model_name='gamebot',
            name='ai',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='bot', to='database.gameai'),
        ),
    ]
