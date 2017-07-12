import React from 'react';
import CenteredLayout from '../../components/CenteredLayout/CenteredLayout';
import {Preloader} from 'react-materialize';

export const Loading = () => (
    <CenteredLayout>
        <Preloader color="red"/>
    </CenteredLayout>
);

export default Loading;
