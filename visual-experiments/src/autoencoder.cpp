#include <utility>

#include <torch/torch.h>
#include <iostream>

struct Discriminator : public torch::nn::Module
{
  Discriminator()
      : m_hidden0 { torch::nn::Linear { n_features, 2048 }, torch::nn::LeakyReLU { opt }, torch::nn::Dropout { 0.3 } }
      , m_hidden1 { torch::nn::Linear { 2048, 1024 }, torch::nn::LeakyReLU { opt }, torch::nn::Dropout { 0.3 } }
      , m_hidden2 { torch::nn::Linear { 1024, 512 }, torch::nn::LeakyReLU { opt }, torch::nn::Dropout { 0.3 } }
      , m_hidden3 { torch::nn::Linear { 512, 256 }, torch::nn::LeakyReLU { opt }, torch::nn::Dropout { 0.3 } }
      , m_hidden4 { torch::nn::Linear { 256, 128 }, torch::nn::LeakyReLU { opt }, torch::nn::Dropout { 0.3 } }
      , m_out { torch::nn::Linear { 128, n_out }, torch::nn::Sigmoid {} } {

      };

  torch::Tensor forward(torch::Tensor input)
  {
    return m_out->forward(
        m_hidden4->forward(m_hidden3->forward(m_hidden2->forward(m_hidden1->forward(m_hidden0->forward(input))))));
  }

  const int n_features = 4096;
  const int n_out = 1;

  torch::nn::LeakyReLUOptions opt;

  torch::nn::Sequential m_hidden0;
  torch::nn::Sequential m_hidden1;
  torch::nn::Sequential m_hidden2;
  torch::nn::Sequential m_hidden3;
  torch::nn::Sequential m_hidden4;
  torch::nn::Sequential m_out;
};

struct Generator : public torch::nn::Module
{
  Generator()
      : m_hidden0 { torch::nn::Linear { n_features, 256 }, torch::nn::LeakyReLU { opt } }
      , m_hidden1 { torch::nn::Linear { 256, 512 }, torch::nn::LeakyReLU { opt } }
      , m_hidden2 { torch::nn::Linear { 512, 1024 }, torch::nn::LeakyReLU { opt } }
      , m_hidden3 { torch::nn::Linear { 1024, 2048 }, torch::nn::LeakyReLU { opt } }
      , m_hidden4 { torch::nn::Linear { 2048, 4096 }, torch::nn::LeakyReLU { opt } }
      , m_out { torch::nn::Linear { 4096, n_out }, torch::nn::Tanh {} }
  {
  }

  torch::Tensor forward(torch::Tensor input)
  {
    return m_out->forward(
        m_hidden4->forward(m_hidden3->forward(m_hidden2->forward(m_hidden1->forward(m_hidden0->forward(input))))));
  }

  const int n_features = 100;
  const int n_out = 4096;

  torch::nn::LeakyReLUOptions opt;

  torch::nn::Sequential m_hidden0;
  torch::nn::Sequential m_hidden1;
  torch::nn::Sequential m_hidden2;
  torch::nn::Sequential m_hidden3;
  torch::nn::Sequential m_hidden4;
  torch::nn::Sequential m_out;
};

torch::Tensor noise(int size)
{
  return torch::randn(size, {});
}

torch::Tensor ones_target(int size)
{
  return torch::ones(size);
}

torch::Tensor zeroes_target(int size)
{
  return torch::zeros(size);
}

std::tuple<torch::Tensor, torch::Tensor, torch::Tensor>
    trainDiscriminator(torch::optim::Optimizer* optim, Generator* generator, Discriminator* discriminator,
                       const torch::Tensor& realData, torch::Tensor fake_data)
{
  auto N = realData.size(0);

  optim->zero_grad();
  auto predictionReal = discriminator->forward(realData);
  auto error_real = torch::l1_loss(predictionReal, ones_target(N));
  error_real.backward();

  auto predictionFake = discriminator->forward(std::move(fake_data));
  auto error_fake = torch::l1_loss(predictionFake, zeroes_target(N));
  error_fake.backward();

  optim->step();

  return std::make_tuple(error_real + error_fake, predictionReal, predictionFake);
}

torch::Tensor trainGenerator(torch::optim::Optimizer* optim, Discriminator* discriminator,
                             const torch::Tensor& fake_data)
{
  auto N = fake_data.size(0);

  optim->zero_grad();

  auto prediction = discriminator->forward(fake_data);
  auto error = torch::l1_loss(prediction, ones_target(N));
  error.backward();

  optim->step();

  return error;
}

int main()
{
  Generator generator;
  Discriminator discriminator;

  torch::optim::Adam discOptimizer(discriminator.parameters(), 0.0002);
  torch::optim::Adam genOptimizer(generator.parameters(), 0.0002);

  torch::nn::BCELoss loss;

  std::cout << generator << std::endl;

  const auto epochs = 200;
  for(auto epoch = 0; epoch < epochs; epoch++)
  {
    for()
  }

  //Hier kommt die magie!
  /*
# Total number of epochs to train
  num_epochs = 200
  for epoch in range(num_epochs):
  for n_batch, (real_batch,_) in enumerate(data_loader):
  N = real_batch.size(0)
# 1. Train Discriminator
  real_data = Variable(images_to_vectors(real_batch))
# Generate fake data and detach
# (so gradients are not calculated for generator)
  fake_data = generator(noise(N)).detach()
# Train D
  d_error, d_pred_real, d_pred_fake = \
              train_discriminator(d_optimizer, real_data, fake_data)

# 2. Train Generator
# Generate fake data
  fake_data = generator(noise(N))
# Train G
  g_error = train_generator(g_optimizer, fake_data)
# Log batch error
  logger.log(d_error, g_error, epoch, n_batch, num_batches)
# Display Progress every few batches
  if (n_batch) % 100 == 0:
  test_images = vectors_to_images(generator(test_noise))
  test_images = test_images.data
  logger.log_images(
      test_images, num_test_samples,
      epoch, n_batch, num_batches
  );
# Display status Logs
  logger.display_status(
      epoch, num_epochs, n_batch, num_batches,
      d_error, g_error, d_pred_real, d_pred_fake
  )
  */
}
