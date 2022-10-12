# Generated by Django 3.1.2 on 2020-12-13 02:26

import database.models
from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0023_problemsubmition_status'),
    ]

    operations = [
        migrations.CreateModel(
            name='ProblemSubmission',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('timestamp', models.DateTimeField(default=django.utils.timezone.now)),
                ('score', models.FloatField(default=0)),
                ('status', models.CharField(default='', max_length=20)),
                ('code', models.FileField(upload_to=database.models.PS_dirpath)),
                ('problem', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='database.problem')),
                ('user', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to=settings.AUTH_USER_MODEL)),
            ],
        ),
        migrations.DeleteModel(
            name='ProblemSubmition',
        ),
    ]
