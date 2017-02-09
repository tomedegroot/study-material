###Nicknames for cron

The first 5 columns of a crontab which indicate the time to execute can also be replaced with nicknames (in most distro's):

1. @reboot
2. @yearly or @annually
3. @monthly 
4. @weekly
5. @daily
6. @hourly

They always run when a period start, so:

```
0 0 * * * command
```

and

```
@daily command
```

are the same.

###Where are crontabs stored?

####User crontabs

The ones edited with `crontab` (user cron) are stored in */var/spool/cron/*. Although you can edit the files in */var/spool/cron/* directly, use the `crontab` command so you get syntax checking.

####System crontab

Stored in:

1. */etc/crontab*/
2. */etc/cron.d*/
3. */etc/cron.{hourly,daily,weekly,monthly}*
