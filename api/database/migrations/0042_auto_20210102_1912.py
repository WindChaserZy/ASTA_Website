# Generated by Django 3.1.4 on 2021-01-02 19:12

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0041_auto_20210102_1842'),
    ]

    operations = [
        migrations.AlterField(
            model_name='problemsubmission',
            name='problem',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, related_name='submissions', to='database.problem'),
        ),
    ]