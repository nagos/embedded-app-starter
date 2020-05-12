WEB интерфейс модуля pbx-mtv-508.


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

Расширение для Chrome
https://augury.angular.io/

Создание новых компонентов по шаблону
Компонент будет автоматически прописан в app.module.ts
(declarations и import)
компонент будет иметь имя суффиикс Component

Команда
ng generate component block
создает BlockComponent в папке src/app/block


Создание компонентов для страниц route
ng generate component main --flat

--flat - создать в корневой папке

Отладка в VS Code
Установить расширение Debugger for Chrome

Иконки FontAwesome 4
https://fontawesome.com/icons?d=gallery&m=free
