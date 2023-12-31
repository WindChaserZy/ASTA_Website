# Generated by Django 3.2.15 on 2022-12-03 20:44

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion
import mdeditor.fields


class Migration(migrations.Migration):

    dependencies = [
        ('database', '0061_alter_material_file'),
    ]

    operations = [
        migrations.CreateModel(
            name='MComment',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('content', mdeditor.fields.MDTextField()),
                ('timestamp', models.DateTimeField(auto_now_add=True)),
                ('author', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to=settings.AUTH_USER_MODEL)),
                ('material', models.ForeignKey(null=True, on_delete=django.db.models.deletion.SET_NULL, to='database.material')),
            ],
        ),
    ]
