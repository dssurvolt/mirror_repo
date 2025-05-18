app.post('/users', async (req, res) => {
    const { name, email } = req.body;
    try {
      await pool.query('INSERT INTO users (name, email) VALUES (?, ?)', [name, email]);
      res.status(201).json({ success: true });
    } catch (err) {
      res.status(500).json({ error: err.message });
    }
  });