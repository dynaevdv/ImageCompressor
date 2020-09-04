# ImageCompressor

Пояснения к проекту:

- Репозиторий состоит из трех веток. Ветки dev и master содержат в себе стадии разработки приложения. Последний коммит в мастер ветке готов для проверки и работает без ошибок. 
Во всех остальных коммитах возможна неправильная работа приложения, т.к. в них уже учитывались возможности реализаций следующих задач, но реализованы эти возможности или еще не были, или это сделано без учета всех возможных вариантов использования.
Ветка other содержит в себе решение задач с 1 по 4. 

- Проект полностью выполняет функции, описанные в задании, но можно было добавить еще несколько функций. Например, можно было добавить параметризуемую генерацию kernel матрицы для фильтрации изображения, или отображение сразу всей пирамиды изображений.
Но проект получился уже и так довольно большой для тестового задания, и как я сказал, требуемые задачи он выполняет.

- Для фильтрации изображения применяется гауссово сглаживание с использованием kernel матрицы (1/4 1/2 1/4). 
Количество итераций фильтрации перед каждым сжатием изображения выбирается пользователем.

- Размер окна приложения можно выбрать в main функции.

- В задании 1 не стал разделять заголовки и имплементацию, чтобы было легче проверять задание. 