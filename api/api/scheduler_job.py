from apscheduler.schedulers.background import BackgroundScheduler
from django_apscheduler.jobstores import DjangoJobStore, register_events, register_job
from judge import tasks

scheduler = BackgroundScheduler()
scheduler.add_jobstore(DjangoJobStore(), "default")
try:
	@register_job(scheduler, "interval", minutes=1, misfire_grace_time=120)
	#@register_job(scheduler, 'cron', day_of_week='mon-sun', hour='8', minute='30', second='10', id='delete_stale_data')
	#@register_job(scheduler, 'date', run_date='2021-02-8 01:56:00')
	def game_task():
		tasks.randomRankingGame()
		
	register_events(scheduler)
	scheduler.start()
except Exception as e:
	print(e)
	try:
		scheduler.shutdown()
	except:
		pass