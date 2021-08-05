Заготовка web интерфейса на Angular 11


Первоначальная установка проекта
npm install

Создать файл debug.ts
=======================================
export const DEV_IP = '192.168.X.X';
=======================================

Запуск отладочного сервера
npm start

Сборка для устройства
npm run build

scp -r dist/* root@192.168.x.x:/www/pages/

Проверка кода на ощибки
npm run lint

Иконки FontAwesome 5
https://fontawesome.com/icons
(нужно импортировать индивидуально в app.module.ts


Эмулятор сервера

node server_emulator.js
В debug.ts прописать
export const DEV_IP = 'localhost:9898';


Команды так же доступны через меню VS Code Терминал-Запуск задачи.
