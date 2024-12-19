// Part 1: Multiple-choice logic
document.querySelectorAll('.answer-btn').forEach(button => {
    button.addEventListener('click', function () {
      document.querySelectorAll('.answer-btn').forEach(btn => {
        btn.classList.remove('correct', 'incorrect');
      });

      // Check if the clicked button is correct
      const isCorrect = this.getAttribute('data-correct') === 'true';
      const feedback = document.getElementById('sisu-feedback');

      if (isCorrect) {
        this.classList.add('correct');
        feedback.textContent = "Correct!";
        feedback.style.color = "green";
      } else {
        this.classList.add('incorrect');
        feedback.textContent = "Incorrect";
        feedback.style.color = "red";
      }
    });
  });

// Part 2: Free response logic
document.getElementById('lake-submit').addEventListener('click', function () {
    const lakeInput = document.getElementById('lake-input');
    const feedback = document.getElementById('lake-feedback');
    const userAnswer = parseInt(lakeInput.value.trim(), 10);
    const correctAnswer = 188000; // Approximate number of lakes in Finland
    const tolerance = 10000; // Acceptable range

    if (isNaN(userAnswer)) {
      lakeInput.classList.add('incorrect');
      lakeInput.classList.remove('correct');
      feedback.textContent = "Please enter a valid number!";
      feedback.style.color = "red";
    } else if (Math.abs(userAnswer - correctAnswer) <= tolerance) {
      lakeInput.classList.add('correct');
      lakeInput.classList.remove('incorrect');
      feedback.textContent = `Correct! Finland has approximately ${correctAnswer} lakes.`;
      feedback.style.color = "green";
    } else {
      lakeInput.classList.add('incorrect');
      lakeInput.classList.remove('correct');
      feedback.textContent = `Incorrect. Finland has approximately ${correctAnswer} lakes.`;
      feedback.style.color = "red";
    }

    lakeInput.value = "";
  });
