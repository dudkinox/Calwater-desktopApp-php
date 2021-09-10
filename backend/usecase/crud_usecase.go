package usecase

import (
	"backend/model"
	"backend/repository"
	"context"
)

type CrudUseCase struct {
	config   *model.EnvConfig
	crudRepo repository.CrudRepositoryI
}

func NewCrudUseCase(config *model.EnvConfig, crudRepo repository.CrudRepositoryI) CrudUseCaseI {
	return &CrudUseCase{
		config:   config,
		crudRepo: crudRepo,
	}
}

func (cuc *CrudUseCase) GetHealthCheck(ctx context.Context) (err error) {
	return
}
