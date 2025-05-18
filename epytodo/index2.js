require('dotenv').config(); // Charger les variables d'environnement
const express = require('express'); // Importer Express
const app = express(); // Créer une instance d'Express
const port = process.env.PORT; // Récupère le port depuis .env

// app.get('/name/:nom', (req, res) => {
//     res.send(`Bonjour ${req.params.nom} !`);
// });

app.get('/name/:nom', (req, res) => {
    const name = req.params.nom;
    const acceptHeader = req.headers.accept || 'text/plain'; // Par défaut : texte
  
    // Réponse selon le Content-Type demandé
    if (acceptHeader.includes('application/json')) {
      res.json({ message: `Bonjour ${name} !` });
    } else if (acceptHeader.includes('text/html')) {
      res.send(`<h1 style="color: blue;">Bonjour ${name} !</h1>`);
    } else {
      res.send(`Bonjour ${name} !`);
    }
});

app.listen(port, () => {
  console.log(`Serveur démarré sur http://localhost:${port}`);
});