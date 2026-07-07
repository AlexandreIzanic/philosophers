/* ===========================================================================
   Composant quiz réutilisable (partagé entre leçons).
   Usage dans une leçon :
     <div class="quiz" data-answer="1">
       <p class="q">Question ?</p>
       <button class="opt">Réponse A</button>
       <button class="opt">Réponse B</button>   <!-- index 1 = bonne -->
       <p class="feedback" data-correct="..." data-wrong="..."></p>
     </div>
   data-answer = index (base 0) du bouton correct.
   Le <p class="feedback"> porte les messages via data-correct / data-wrong.
   =========================================================================== */
(function () {
  function initQuiz(quiz) {
    var answer = parseInt(quiz.getAttribute("data-answer"), 10);
    var opts = quiz.querySelectorAll(".opt");
    var feedback = quiz.querySelector(".feedback");
    opts.forEach(function (opt, i) {
      opt.addEventListener("click", function () {
        opts.forEach(function (o) { o.disabled = true; });
        if (i === answer) {
          opt.classList.add("correct");
          if (feedback) {
            feedback.textContent = feedback.getAttribute("data-correct") || "Correct.";
            feedback.className = "feedback correct";
          }
        } else {
          opt.classList.add("wrong");
          opts[answer].classList.add("correct");
          if (feedback) {
            feedback.textContent = feedback.getAttribute("data-wrong") || "Pas tout à fait.";
            feedback.className = "feedback wrong";
          }
        }
      });
    });
  }
  document.addEventListener("DOMContentLoaded", function () {
    document.querySelectorAll(".quiz").forEach(initQuiz);
  });
})();
