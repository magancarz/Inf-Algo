//importuj moduł express
const express = require('express');
const mongoose = require('mongoose');
const ejs = require('ejs');
const jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');

const user = {
  id: '1',
  username: 'mati',
  email: 'mati@example.com',
  role: 'mati'
};
const secretKey = 'secret-key';
const token = jwt.sign(user, secretKey, { expiresIn: '1h' });

//umożliwia obsługę metod HTTP, takich jak PUT i DELETE (nie są natywnie obsługiwane)
const methodOverride = require('method-override');
const app = express();
const port = 3000;

//middleware, który parsuje dane z formularzy URL-encoded i umieszcza je w req.body
app.use(express.urlencoded({ extended: true }));
app.use(methodOverride('_method'));
app.use(express.static('public'));

// Konfiguracja silnika widoków EJS
app.set('view engine', 'ejs');

const authenticateJWT = (req, res, next) => {
  jwt.verify(token, 'secret-key', (err, user) => {
    if (err) {
      return res.status(403).json({ message: 'Invalid or expired token' });
    }
    req.user = user;
    next();
  });
};

// Połączenie z bazą danych MongoDB
mongoose.connect("mongodb+srv://261694:jsnUyLPRCsN7uNNt@www.7kcg2xe.mongodb.net/?retryWrites=true&w=majority", { 
  useNewUrlParser: true,
   useUnifiedTopology: true })
  .then(() => {
    console.log('Połączono z bazą danych MongoDB');
  })
  .catch((err) => {
    console.error('Błąd podczas łączenia z bazą danych', err);
  });

// Schemat i model notatki
const noteSchema = new mongoose.Schema({
  title: String,
  content: String,
});

//model reprezentuje kolekcję notatek 
const Note = mongoose.model('Note', noteSchema);

//parsowanie danych w formacie JSON
app.use(express.json());

// Start serwera
app.listen(port, () => {
  console.log(`Serwer uruchomiony na porcie ${port}`);
});

// Endpointy

//strona główna (dodawanie notatki)
app.get('/', (req, res) => {
  //renderowanie widoku
  res.render('index', { successMessage: false });
});

//pobiera wszystkie notatki z bazy danych i renderuje widok notes (dodatkowo przekazuje notatki)
app.get('/note', authenticateJWT, (req, res) => {
  Note.find({})
    .then((notes) => {
      res.render('notes', { notes });
    })
    .catch((err) => {
      console.error('Błąd podczas pobierania notatek', err);
      res.status(500).json({ message: 'Wystąpił błąd serwera' });
    });
});

//szuka i wyświetla konketną notatkę
app.get('/note/:id', authenticateJWT, (req, res) => {
  const noteId = req.params.id;
  Note.findById(noteId)
    .then((note) => {
      if (!note) {
        return res.status(404).json({ message: 'Nie istnieje notatka o podanym identyfikatorze' });
      }

     res.render('note', { note });
     // return res.status;
    })
    .catch((err) => {
      console.error('Błąd podczas pobierania notatki', err);
      res.status(500).json({ message: 'Wystąpił błąd serwera' });
    });
});

//dodawanie notatki
app.post('/', authenticateJWT, (req, res) => {
  //pobiera przekazane wartości z body
  const { title, content } = req.body;

  //tworzy nową notatkę
  const newNote = new Note({ title, content });
  newNote.save()
    .then((savedNote) => {
      // jeśli poprawnie dodano notatke to wyswietl informacje
      const successMessage = true;
      res.status(201).render('index', { successMessage: "Notatka została dodana"});
    })
    .catch((err) => {
      console.error('Błąd podczas zapisywania notatki', err);
      res.status(500).json({ message: 'Wystąpił błąd serwera' });
    });
});

//Edycja notatki 
app.put('/note/:id', authenticateJWT, (req, res) => {
  const noteId = req.params.id;
  const { title, content } = req.body;

  //aktualizuje notatkę o noteId
  Note.findByIdAndUpdate(noteId, { title, content }, { new: true })
    .then((updatedNote) => {
      if (!updatedNote) {
        return res.status(404).json({ message: 'Nie istnieje notatka o podanym identyfikatorze' });
      }

      res.status(200).redirect('/note');
    })
    .catch((err) => {
      console.error('Błąd podczas aktualizacji notatki', err);
      res.status(500).json({ message: 'Wystąpił błąd serwera' });
    });
});

//Usuwanie notatki
app.delete('/note/:id', authenticateJWT, (req, res) => {
  const noteId = req.params.id;

  Note.deleteOne({ _id: noteId })
    .then((result) => {
      if (result.deletedCount === 0) {
        return res.status(404).json({ message: 'Nie istnieje notatka o podanym identyfikatorze' });
      }

      res.status(200).redirect('/note');
    })
    .catch((err) => {
      console.error('Błąd podczas usuwania notatki', err);
      res.status(500).json({ message: 'Wystąpił błąd serwera' });
    });
});