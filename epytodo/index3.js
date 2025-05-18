require('dotenv').config(); // Charger les variables d'environnement
const express = require('express'); // Importer Express
const app = express(); // Créer une instance d'Express
const port = process.env.PORT; // Récupère le port depuis .env

app.get('/date', (req, res) => {
    const date = new Date().toISOString().split('T')[0];
    
    // Gérer le Content-Type
    if (req.headers.accept === 'application/json') {
      res.json({ date });
    } else {
      res.send(`<h1>Date du jour : ${date}</h1>`);
    }
});

app.listen(port, () => {
  console.log(`Serveur démarré sur http://localhost:${port}`);
});