-- 1. Сначала полностью очищаем все таблицы, чтобы не было дублей
-- CASCADE удалит данные во всех связанных таблицах сразу
TRUNCATE Genres, Artists, ArtistGenres, Albums, ArtistAlbums, Tracks, Collections, CollectionTracks RESTART IDENTITY CASCADE;

-- 2. Теперь добавляем данные с нуля
INSERT INTO Genres (name) VALUES ('Rock'), ('Pop'), ('Hip-Hop'), ('Jazz'), ('Electronic');

INSERT INTO Artists (name) VALUES ('Linkin Park'), ('Madonna'), ('Eminem'), ('Gorillaz'), ('Moby'), ('The Weeknd'), ('Daft Punk'), ('Lady Gaga');

INSERT INTO ArtistGenres (artist_id, genre_id) VALUES (1, 1), (2, 2), (3, 3), (4, 1), (4, 3), (5, 5), (6, 2), (7, 5), (8, 2);

INSERT INTO Albums (title, release_year) VALUES ('Meteora', 2003), ('Ray of Light', 1998), ('Music To Be Murdered By', 2020), ('Demon Days', 2005), ('Play', 1999), ('After Hours', 2020), ('Random Access Memories', 2013), ('Chromatica', 2020);

INSERT INTO ArtistAlbums (artist_id, album_id) VALUES (1, 1), (2, 2), (3, 3), (4, 4), (5, 5), (6, 6), (7, 7), (8, 8);

INSERT INTO Tracks (title, duration, album_id) VALUES 
('Numb', 187, 1), ('Frozen', 361, 2), ('Godzilla', 211, 3), 
('Feel Good Inc', 221, 4), ('Porcelain', 241, 5), ('Blinding Lights', 200, 6), 
('Get Lucky', 368, 7), ('Rain On Me', 182, 8), ('In the End', 216, 1), ('My Name Is', 268, 3);

INSERT INTO Collections (title, release_year) VALUES 
('Best of 2020', 2020), ('Top Hits', 2019), ('Chill Mix', 2021), 
('Rock Classics', 2010), ('Electronic Vibes', 2018), ('Workout Playlist', 2022),
('Evening Jazz', 2017), ('Driving Songs', 2020);

INSERT INTO CollectionTracks (collection_id, track_id) VALUES (1, 3), (1, 6), (1, 8), (2, 1), (2, 10), (3, 5), (5, 7), (8, 6);

SELECT title, duration 
FROM Tracks
ORDER BY duration DESC
LIMIT 1;

SELECT title 
FROM Tracks
WHERE duration >= 210;

SELECT title 
FROM Collections
WHERE release_year BETWEEN 2018 AND 2020;

SELECT name 
FROM Artists
WHERE name NOT LIKE '% %';

SELECT title 
FROM Tracks
WHERE title ILIKE '%my%' OR title ILIKE '%мой%';




