-- 1. Количество исполнителей в каждом жанре
-- Группируем по названию жанра и считаем ID исполнителей
SELECT g.name, COUNT(ag.artist_id) AS artist_count
FROM Genres g
JOIN ArtistGenres ag ON g.id = ag.genre_id
GROUP BY g.name;

-- 2. Количество треков, вошедших в альбомы 2019–2020 годов
-- Связываем треки с альбомами и фильтруем по году
SELECT COUNT(t.id) AS track_count
FROM Tracks t
JOIN Albums a ON t.album_id = a.id
WHERE a.release_year BETWEEN 2019 AND 2020;

-- 3. Средняя продолжительность треков по каждому альбому
-- Используем функцию AVG и группируем по названию альбома
SELECT a.title, AVG(t.duration) AS avg_duration
FROM Albums a
JOIN Tracks t ON a.id = t.album_id
GROUP BY a.title;

-- 4. Все исполнители, которые не выпустили альбомы в 2020 году
-- Используем исключающий подзапрос (находим тех, кто выпускал, и берем всех остальных)
SELECT name
FROM Artists
WHERE name NOT IN (
    SELECT ar.name
    FROM Artists ar
    JOIN ArtistAlbums aa ON ar.id = aa.artist_id
    JOIN Albums al ON aa.album_id = al.id
    WHERE al.release_year = 2020
);

-- 5. Названия сборников, в которых присутствует конкретный исполнитель
-- Выберем, например, 'Linkin Park' 
SELECT DISTINCT c.title
FROM Collections c
JOIN CollectionTracks ct ON c.id = ct.collection_id
JOIN Tracks t ON ct.track_id = t.id
JOIN Albums a ON t.album_id = a.id
JOIN ArtistAlbums aa ON a.id = aa.album_id
JOIN Artists ar ON aa.artist_id = ar.id
WHERE ar.name = 'Linkin Park';
