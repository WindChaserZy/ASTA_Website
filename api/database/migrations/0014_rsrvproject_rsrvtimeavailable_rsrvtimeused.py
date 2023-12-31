# Generated by Django 3.0.2 on 2020-10-05 10:57

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion
import mdeditor.fields


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0013_auto_20200922_0018'),
    ]

    operations = [
        migrations.CreateModel(
            name='RsrvProject',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(default='', max_length=50)),
                ('intro', mdeditor.fields.MDTextField()),
                ('contest', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='database.Contest')),
            ],
        ),
        migrations.CreateModel(
            name='RsrvTimeAvailable',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('startTime', models.DateTimeField()),
                ('endTime', models.DateTimeField()),
                ('project', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='database.RsrvProject')),
            ],
        ),
        migrations.CreateModel(
            name='RsrvTimeUsed',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('startTime', models.DateTimeField()),
                ('endTime', models.DateTimeField()),
                ('availableTime', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='database.RsrvTimeAvailable')),
                ('user', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to=settings.AUTH_USER_MODEL)),
            ],
        ),
    ]
