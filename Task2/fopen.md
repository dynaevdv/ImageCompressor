**Предложите исправление представленого ниже кода**

 ```C
FILE *f = fopen(name, "w");
fclose(f);
 ```

fclose() выбрасывает exception в том случае, если f == NULL.
Это может произойти, например, из-за invalid filename. 
Значит нужна следующая проверка:

```C
FILE *f = fopen(name, "w");

if (f != NULL)
{
    flose(f);
}
```







