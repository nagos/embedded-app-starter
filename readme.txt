Заготовка web интерфейса на Angular 9


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


Иконки FontAwesome 5
https://fontawesome.com/icons
(нужно импортировать индивидуально в app.module.ts


Эмулятор сервера

npm install --no-save websocket
node server_emulator.js
В debug.ts прописать
export const DEV_IP = '127.0.0.1:9898';
