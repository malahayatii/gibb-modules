const express = require('express');
const app = express();

let status = 'Inactive'; // Default status

// Endpoint to get the current status
app.get('/status', (req, res) => {
  res.send(status);
});

// Endpoint to receive POST requests from Arduino
app.post('/trigger', (req, res) => {
  // Set status to Active
  status = 'Active';
  console.log('Status updated to Active');

  // Revert status to Inactive after 10 seconds
  setTimeout(() => {
    status = 'Inactive';
    console.log('Status reverted to Inactive');
  }, 10000);

  res.sendStatus(200); // Respond to Arduino
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});