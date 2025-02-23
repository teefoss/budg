`budg` is a super-simple cl budget program.

Given an initial budget for the month, it tells you how much you should have left based on how far into the month it is. For example, on the 15th:

```
$ budg 2000
Current funds should be 1000.
```

Optionally, if you also give it your the remaining funds, it tells you how far over or under budget you are, and how much you can spend per day without going over budget. For example, on the 15th:

```
$ budg 2000 1100
Current funds should be 1000.
You are under budget by 100.
There are 15 days left; spend limit of 73 per day.
```
