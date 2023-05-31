#include <opencv2/opencv.hpp>

int main()
{
    // Connextion à la caméra
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cout << "Erreur lors de la connexion à la caméra" << std::endl;
        return -1;
    }

    // Création de la fenêtre
    cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);

    // Boucle principale
    while (true)
    {
        // Acquisition d'une image
        cv::Mat frame;
        cap >> frame;

        // Affichage de l'image
        cv::imshow("Camera", frame);

        // Attente de 10ms
        if (cv::waitKey(10) == 27)
            break;
    }

    // Fermeture de la fenêtre
    cv::destroyWindow("Camera");

    return 0;
}
