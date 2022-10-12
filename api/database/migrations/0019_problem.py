# Generated by Django 3.1.2 on 2020-12-12 18:07

from django.db import migrations, models
import mdeditor.fields


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0018_rsrvproject_timelimit'),
    ]

    operations = [
        migrations.CreateModel(
            name='Problem',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('title', models.CharField(default='', max_length=128)),
                ('content', mdeditor.fields.MDTextField()),
                ('addTime', models.DateTimeField()),
            ],
        ),
    ]
