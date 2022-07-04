# nex-af

Данная библиотека является standalone версией анти-флуда автовызываемых функций из [Nex-AC](https://github.com/NexiusTailer/Nex-AC) и содержит в себе защиту для большинства стандартных пабликов (полный их список можно посмотреть в начале скрипта).

Также имеется механизм предотвращения флуда между пабликами, когда читер слишком быстро вызывает разные паблики в произвольном порядке. Данная опция называется "Cross-public" anti-flood.

Скрипт игнорирует NPC, если какие-то паблики были быстро вызваны ими.

Настройки по умолчанию заданы в начале файла в двумерном массиве, где первое значение отвечает за минимальную задержку между двумя вызовами паблика, а второе значение задаёт максимальное количество попыток флуда, после которого игрок будет кикнут с сервера.

Все нововведения вносятся в оригинальный античит его автором и эта версия не гарантирует актуальность алгоритмов, которые на данный момент реализованы в Nex-AC. Рекомендуется использовать полноценный античит.
