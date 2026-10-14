#include <iostream>
#include <Windows.h>

double Drinks[4][4]{ { 600, 350, 510, 498 }, { 598, 198, 300 }, { 798, 698 }, { 400 } };
double ShopCart[4][4]{};

int main()
{
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
	srand(time(NULL));

	int choose = 0, amount = 0;
	int hawthornLiters = 11;
	double sum = 0, discount = 0, bonusLiters = 0;
	bool noHawthorn = false;


	while (true)
	{
		system("cls");
		std::cout << "\n\n\n\t\tМагазин \"Соки Александра\"\n\n\n";
		std::cout << "1 - Купить\n";
		std::cout << "2 - Посмотреть ассортимент\n";
		std::cout << "3 - Выйти\n";
		std::cin >> choose;
		if (choose == 1)
		{
			int choose2 = 0;
			system("cls");
			std::cout << "Что вы хотите купить?\n";
			std::cout << "Фруктовые соки:\n1 - Апельсиновый (600руб за 1л)\n2 - Яблочный (350руб за 1л)\n3 - Абрикосовый (510руб за 1л)\n4 - Грушевый (498руб за 1л)\n\n";
			std::cout << "Овощные соки:\n5 - Томатный (598руб за 1л)\n6 - Луковый (198руб за 1л)\n7 - Огуречный (300руб за 1л)\n\n";
			std::cout << "Чаи:\n8 - Чесночный (798руб за 1л)\n9 - Петрушевый (698руб за 1л)\n\n";
			std::cout << "Настойки:\n10 - Боярышник (400 рублей за 1л)\n\n";
			std::cin >> choose2;
			int row = -1, col = -1;
			switch (choose2)
			{
			case 1: row = 0; col = 0; break; // Апельсиновый сок
			case 2: row = 0; col = 1; break; // Яблочный сок
			case 3: row = 0; col = 2; break; // Абрикосовый сок
			case 4: row = 0; col = 3; break; // Грушевый сок
			case 5: row = 1; col = 0; break; // Томатный сок
			case 6: row = 1; col = 1; break; // Луковый сок
			case 7: row = 1; col = 2; break; // Огуречный сок
			case 8: row = 2; col = 0; break; // Чесночный чай
			case 9: row = 2; col = 1; break; // Петрушевый чай
			case 10: row = 3; col = 0; break; // Боярышник 
			default:
				std::cout << "Неверный выбор товара!\n";
				Sleep(1000);
				break;
			}

			if (row != -1 && col != -1)
			{
				system("cls");
				std::cout << "Сколько литров вы хотите взять? ";
				std::cin >> amount;
				if (row == 3 && col == 0)
				{
					int alreadyInCart = (int)ShopCart[3][0];
					if (alreadyInCart + amount > hawthornLiters)
					{
						int canAdd = hawthornLiters - alreadyInCart;
						if (canAdd < 0) canAdd = 0;
						std::cout << "На складе нет столько боярышника! Вам выдадется доступный максимум: " << hawthornLiters << " литров.\n";
						std::cout << "В корзине уже: " << alreadyInCart << "л Можно добавить ещё: " << canAdd << "л.\n";
						amount = canAdd;
						Sleep(2500);
					}
				}

				if (amount > 0)
				{
					ShopCart[row][col] += amount;
					std::cout << "Товар добавлен в корзину!\n";
				}
				else
				{
					std::cout << "Количество должно быть больше 0!\n";
				}
				Sleep(1000);
			}

			sum = 0;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					sum += ShopCart[i][j] * Drinks[i][j];
				}
			}

			int onionLiters = (int)ShopCart[1][1];

			bonusLiters = onionLiters / 4;
			if (bonusLiters > 0)
			{
				discount += bonusLiters * Drinks[1][1];
			}

			if (ShopCart[2][1] >= 3)
			{
				discount += ShopCart[2][1] * Drinks[2][1] * 0.05;
			}

			double fruitLiters = ShopCart[0][0] + ShopCart[0][1] + ShopCart[0][2] + ShopCart[0][3];
			if (ShopCart[3][0] >= 1 && fruitLiters >= 1)
			{
				noHawthorn = true;
				discount += ShopCart[3][0] * Drinks[3][0];
			}

			double afterFirstDiscounts = sum - discount;
			if (afterFirstDiscounts > 3899)
			{
				discount += afterFirstDiscounts * 0.13;
			}
			


				double finalSum = sum - discount;
				if (finalSum < 0) finalSum = 0;

				if (sum > 0)
				{
					system("cls");
					std::cout << "Сумма вашей корзины: " << sum << " руб.\n";

					if (bonusLiters > 0)
						std::cout << "Акция: каждый 4-й литр лукового сока в подарок (-" << bonusLiters * Drinks[1][1] << " руб.)\n";
					if (ShopCart[2][1] >= 3)
						std::cout << "Акция: скидка 5% на 3 литра петрушевого чая (-" << ShopCart[2][1] * Drinks[2][1] * 0.05 << " руб.)\n";
					if (noHawthorn)
						std::cout << "Акция: боярышник вам не доступен когда вы берёте фруктовый сок\n";
					if (afterFirstDiscounts > 3899)
						std::cout << "Акция: скидка 13% на чек (-" << afterFirstDiscounts * 0.13 << " руб.)\n";

					system("pause");

					std::cout << "Итого к оплате: " << finalSum << " руб.\n";
					std::cout << "1 - Оплатить\n";
					std::cout << "2 - Продолжить покупки\n";
					int payChoice;
					std::cin >> payChoice;

					if (payChoice == 1)
					{
						std::cout << "Оплата прошла успешно! Спасибо за покупку!\n";
						std::cout << "Итоговая сумма: " << finalSum << " руб.\n";
						sum = 0;
						Sleep(2000);
						for (int i = 0; i < 4; i++)
						{
							for (int j = 0; j < 4; j++)
							{
								ShopCart[i][j] = 0;
								discount = 0;
								noHawthorn = false;
							}
						}

					}
				}
			}



			else if (choose == 2)
			{
				int choose1 = 0;
				std::cout << "Наши соки из натуральных продуктов и являются лучшими во всём мире!\n";
				std::cout << "Фруктовые соки:\nАпельсиновый (600руб за 1л)\nЯблочный (350руб за 1л)\nАбрикосовый (510руб за 1л)\nГрушевый (498руб за 1л)\n\n";
				std::cout << "Овощные соки:\nТоматный (598руб за 1л)\nЛуковый (198руб за 1л)\nОгуречный (300руб за 1л)\n\n";
				std::cout << "Так же в нашем ассортименте чаи из натуральных трав (прямиком из Китая)\n";
				std::cout << "Чаи:\nЧесночный (798руб за 1л)\nПетрушевый (698руб за 1л)\n\n";
				std::cout << "Настойки:\nБоярышник (400 рублей за 1л)\n\n";
				Sleep(6000);
				std::cout << "Заинтересовал ли вас наш ассортимент?\n1 - Да, я готов купить\n2 - Как нибудь в следующий раз\n";
				std::cin >> choose1;
				if (choose1 == 1)
				{
					system("cls");
				}
				if (choose1 == 2)
				{
					std::cout << "\nДо скорых встреч!\n";
					Sleep(1000);
					break;
				}
			}

			else if (choose == 3)
			{
				std::cout << "\nДо скорых встреч!\n";
				Sleep(1000);
				break;
			}

			else
			{
				std::cout << "\n!!!НЕКОРРЕКТНЫЙ ВВОД, ВВЕДИТЕ НУЖНОЕ ЗНАЧЕНИЕ!!!\n";
				Sleep(1000);
				break;
			}
		}



		return 0;
	}
