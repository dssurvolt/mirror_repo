require('dotenv').config(); // Charger les variables d'environnement
const express = require('express'); // Importer Express
const app = express(); // Créer une instance d'Express
const port = process.env.PORT; // Récupère le port depuis .env

app.get('/', (req, res) => {
  res.send('Hello World!');
});

app.listen(port, () => {
  console.log(`Serveur démarré sur http://localhost:${port}`);
});