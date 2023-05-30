/*const jwt = require('jsonwebtoken');

// Funkcja do generowania tokena JWT
const generateToken = (userId) => {
  const token = jwt.sign({ userId }, 'my-secret-key', { expiresIn: '1h' });
  return token;
};

// Kontroler do logowania użytkownika
const login = (req, res) => {
  // Przykład logowania - sprawdzanie poprawności danych użytkownika
  const { username, password } = req.body;
  if (username === 'admin' && password === 'admin') {
    const token = generateToken(1); // Przykładowe przypisanie identyfikatora użytkownika
    res.json({ token });
  } else {
    res.status(401).json({ message: 'Nieprawidłowe dane logowania' });
  }
};

module.exports = { login };
*/

// Funkcja do generowania tokena JWT
const generateToken = (userId) => {
  const token = jwt.sign({ userId }, 'my-secret-key', { expiresIn: '1h' });
  return token;
};

// Kontroler do logowania użytkownika
const login = (req, res) => {
  // Przykład logowania - sprawdzanie poprawności danych użytkownika
  const { username, password } = req.body;
  if (username === 'admin' && password === 'admin') {
    const token = generateToken(1); // Przykładowe przypisanie identyfikatora użytkownika
    res.json({ token });
  } else {
    res.status(401).json({ message: 'Nieprawidłowe dane logowania' });
  }
};

// Eksportuj funkcję login
export { login };
