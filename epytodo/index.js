const express = require('express');
const app = express();
const port = process.env.PORT || 3000; // Utilise le port du .env ou 3000
const bodyParser = require('body-parser');
app.use(bodyParser.json()); // Pour parser le JSON

app.get('/', (req, res) => {
  res.send('Hello World!');
});

app.listen(port, () => {
  console.log(`Serveur démarré sur http://localhost:${port}`);
});