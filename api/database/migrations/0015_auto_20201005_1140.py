# Generated by Django 3.0.2 on 2020-10-05 11:40

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0014_rsrvproject_rsrvtimeavailable_rsrvtimeused'),
    ]

    operations = [
        migrations.AlterField(
            model_name='rsrvtimeavailable',
            name='project',
            field=models.ForeignKey(blank=True, null=True, on_delete=django.db.models.deletion.SET_NULL, to='database.RsrvProject'),
        ),
        migrations.AlterField(
            model_name='user',
            name='className',
            field=models.CharField(blank=True, default='', max_length=10),
        ),
        migrations.AlterField(
            model_name='user',
            name='email',
            field=models.CharField(blank=True, default='', max_length=60),
        ),
        migrations.AlterField(
            model_name='user',
            name='name',
            field=models.CharField(blank=True, default='', max_length=20),
        ),
    ]
