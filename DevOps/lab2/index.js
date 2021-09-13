const express = require('express')
const app = express()
const port = 3000

app.get('/', (req, res) => {
  res.send('Lab 2, branch: master !')
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})