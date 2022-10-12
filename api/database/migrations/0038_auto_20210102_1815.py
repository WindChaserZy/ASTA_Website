# Generated by Django 3.1.4 on 2021-01-02 18:15

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0037_contest_timeup'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='contest',
            name='problems',
        ),
        migrations.AddField(
            model_name='problem',
            name='contest',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, related_name='problems', to='database.contest'),
        ),
        migrations.AddField(
            model_name='problem',
            name='weight',
            field=models.FloatField(default=1),
        ),
    ]
